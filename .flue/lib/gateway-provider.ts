/* oxlint-disable */
// Route flue model traffic through the user's gateway (gateway.sammy.sh).
//
// pi-ai's built-in catalog has no "grok-composer-2.5-fast" and hardcodes the
// xai base URL to https://api.x.ai/v1, so a bare OPENAI_BASE_URL/ANTHROPIC_BASE_URL
// env var is ignored for xai models. registerProvider() installs a URL-prefix
// provider that BYPASSES the catalog: a model id of the form "gateway/<wire-id>"
// resolves to an openai-completions request against baseUrl, sending the wire
// model "<wire-id>". So "gateway/xai/grok-composer-2.5-fast" =>
// POST {baseUrl}/chat/completions  with  model: "xai/grok-composer-2.5-fast".
import { registerProvider } from "@flue/runtime/app";

registerProvider("gateway", {
  api: "openai-completions",
  baseUrl: process.env.OPENAI_BASE_URL ?? "https://gateway.sammy.sh/v1",
  apiKey: process.env.OPENAI_API_KEY ?? "sk-dummy",
});

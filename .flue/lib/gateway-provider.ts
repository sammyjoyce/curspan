/* oxlint-disable */
// Route flue model traffic through the user's gateway (gateway.sammy.sh).
//
// xai models are served via the gateway's OpenAI *Responses* API, so this uses
// api "openai-responses" -> pi-ai POSTs to {baseUrl}/responses (i.e.
// https://gateway.sammy.sh/v1/responses). registerProvider() installs a
// URL-prefix provider that BYPASSES pi-ai's built-in catalog: a model id of the
// form "gateway/<wire-id>" resolves to a responses-API request against baseUrl,
// sending the wire model "<wire-id>". So "gateway/xai/grok-composer-2.5-fast"
// => POST {baseUrl}/responses  with  model: "xai/grok-composer-2.5-fast".
import { registerProvider } from "@flue/runtime/app";

registerProvider("gateway", {
  api: "openai-responses",
  baseUrl: process.env.OPENAI_BASE_URL ?? "https://gateway.sammy.sh/v1",
  apiKey: process.env.OPENAI_API_KEY ?? "sk-dummy",
  contextWindow: 256000,
  maxTokens: 32768,
});

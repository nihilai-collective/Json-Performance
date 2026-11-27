
----
### Canada Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 1279.5 | 0.298185 | 6545.91ms | 5212421 | 80 | 1.07365e+10 | 3.88509e+06 | 5.07053 | -(Win) | false |
| simdjson (ondemand) | 1187.87 | 0.29033 | 7155.1ms | 5212421 | 40 | 5.90455e+09 | 4.18476e+06 | 0.489073 | 2(Loss) | true |

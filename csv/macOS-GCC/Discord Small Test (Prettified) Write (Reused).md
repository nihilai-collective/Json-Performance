
----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13965.3 | 2.22897 | 56.585ms | 7376 | 2560 | 322694 | 503.7 | 0.138779 | 1(Win) | true |
| Glaze | 2428.3 | 1.02645 | 319.478ms | 7376 | 320 | 282919 | 2896.8 | 0.95733 | 2(Loss) | true |
| simdjson (reflection) | 332.145 | 0.509157 | 2105.65ms | 7376 | 320 | 3.72083e+06 | 21178.4 | 0.162166 | 3(Loss) | true |

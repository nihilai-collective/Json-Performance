
----
### Canada Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5791.3 | 0.4173 | 6506.82ms | 6661989 | 320 | 6.70661e+09 | 1.09705e+06 | 1.15471 | 1(Win) | true |
| Glaze | 4121.14 | 0.101504 | 9857.57ms | 6661897 | 30 | 7.34591e+07 | 1.54163e+06 | 0.0088572 | 2(Loss) | true |
| simdjson (reflection) | 303.543 | 0.787486 | 6423.61ms | 6661989 | 30 | 8.15034e+11 | 2.09307e+07 | 4.30719 | 3(Loss) | true |

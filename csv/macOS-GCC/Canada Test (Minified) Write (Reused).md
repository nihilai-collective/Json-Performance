
----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2225.28 | 0.433798 | 5652.32ms | 2090234 | 320 | 4.8322e+09 | 895798 | 0.283544 | 1(Win) | true |
| Glaze | 1556.38 | 1.20518 | 8044.93ms | 2090234 | 30 | 7.14804e+09 | 1.28079e+06 | 0.197601 | 2(Loss) | true |
| simdjson (reflection) | 723.589 | 0.759882 | 8387.97ms | 2090326 | 30 | 1.31479e+10 | 2.755e+06 | 0.558464 | 3(Loss) | true |


----
### Canada Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1285.22 | 0.13064 | 9864.85ms | 2090326 | 30 | 1.23181e+08 | 1.55108e+06 | 0.335512 | 1.92621 | 1(Win) | true |
| Glaze | 687.98 | 0.358354 | 9489.4ms | 2090234 | 40 | 4.31243e+09 | 2.89747e+06 | 0.0438506 | 3.59848 | 2(Loss) | true |

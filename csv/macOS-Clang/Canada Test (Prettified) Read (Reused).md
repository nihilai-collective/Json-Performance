
----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1364.03 | 0.131908 | 6363.12ms | 5212421 | 80 | 1.8487e+09 | 3.64431e+06 | 0.0732114 | 1(Win) | true |
| simdjson (ondemand) | 1298.54 | 0.237537 | 6619.33ms | 5212421 | 80 | 6.6149e+09 | 3.82811e+06 | 0.338327 | 2(Loss) | true |

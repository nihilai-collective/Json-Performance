
----
### Canada Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 620.422 | 0.392901 | 5864.33ms | 2090234 | 30 | 4.78083e+09 | 3.21298e+06 | 4.62559 | 1(Win) | true |
| Jsonifier (generic) | 604.29 | 0.483475 | 5771.94ms | 2090234 | 80 | 2.03487e+10 | 3.29875e+06 | 0.01387 | 2(Loss) | true |

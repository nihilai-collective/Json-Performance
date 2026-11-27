
----
### Github Events Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2365.14 | 0.0247965 | 2700.58ms | 53331 | 80 | 2274.68 | 21504.2 | 0.0147043 | 1(Win) | true |
| Jsonifier (two-stage) | 2060.93 | 0.0568377 | 3009.95ms | 53331 | 4890 | 962090 | 24678.4 | 0.0583114 | 2(Loss) | true |
| Glaze | 1871.99 | 0.14303 | 3149.6ms | 53331 | 640 | 966474 | 27169.2 | 0.185162 | 3(Loss) | true |
| simdjson (ondemand) | 1021.42 | 0.058173 | 5590.98ms | 53331 | 4890 | 4.10304e+06 | 49794 | 0.18383 | 4(Loss) | true |

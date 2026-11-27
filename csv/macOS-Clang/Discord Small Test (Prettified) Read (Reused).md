
----
### Discord Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2576.65 | 0.0944981 | 265.289ms | 6701 | 80 | 439.445 | 2480.19 | 0.00352783 | 1(Win) | true |
| Jsonifier (two-stage) | 2409.69 | 0.0698989 | 282.656ms | 6701 | 160 | 549.817 | 2652.03 | 0.0619424 | 2(Loss) | true |
| Glaze | 2099.08 | 0.408267 | 339.935ms | 6701 | 30 | 4634.81 | 3044.47 | 1.48222 | 3(Loss) | true |
| simdjson (ondemand) | 940.008 | 0.111397 | 679.277ms | 6701 | 80 | 4588.35 | 6798.43 | 0.486289 | 4(Loss) | true |

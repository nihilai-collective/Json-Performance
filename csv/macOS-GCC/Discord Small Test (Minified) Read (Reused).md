
----
### Discord Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2545.61 | 0.610151 | 227.486ms | 4857 | 1280 | 157774 | 1819.6 | 0.437733 | 1(Win) | true |
| Glaze | 2083.76 | 0.291952 | 264.851ms | 4857 | 4890 | 205955 | 2222.91 | 0.24384 | 2(Loss) | true |
| Jsonifier (two-stage) | 1787.04 | 3.06641 | 324.134ms | 4857 | 40 | 252692 | 2592 | 0.409836 | 3(Loss) | true |
| simdjson (reflection) | 1313.59 | 0.220345 | 397.147ms | 4857 | 4890 | 295210 | 3526.2 | 0.246013 | 4(Loss) | true |
| simdjson (ondemand) | 1185.85 | 0.155743 | 430.31ms | 4857 | 4890 | 180969 | 3906.07 | 0.405313 | 5(Loss) | true |

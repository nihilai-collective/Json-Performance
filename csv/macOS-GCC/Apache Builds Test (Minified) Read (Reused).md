
----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1985.42 | 0.197649 | 7252.39ms | 94653 | 30 | 242257 | 45465.6 | 1.76991 | 1(Win) | true |
| Glaze | 1418.55 | 0.298463 | 8489.75ms | 94653 | 4890 | 1.76388e+08 | 63634.1 | 0.136373 | 2(Loss) | true |
| Jsonifier (two-stage) | 1289.51 | 0.517567 | 9464ms | 94653 | 640 | 8.40106e+07 | 70002 | 0.151195 | 3(Loss) | true |
| simdjson (reflection) | 1017.54 | 0.431474 | 5702.05ms | 94653 | 1280 | 1.87535e+08 | 88711.8 | 0.827926 | 4(Loss) | true |
| simdjson (ondemand) | 879.505 | 0.497109 | 6495.17ms | 94653 | 320 | 8.33001e+07 | 102635 | 1.31534 | 5(Loss) | true |

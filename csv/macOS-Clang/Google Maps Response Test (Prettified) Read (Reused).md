
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2830.75 | 0.0491878 | 896.095ms | 25388 | 40 | 707.994 | 8553.17 | 0.0207568 | 1(Win) | true |
| Jsonifier (two-stage) | 2391.63 | 0.0666305 | 1072.37ms | 25388 | 4890 | 222497 | 10123.6 | 0.102423 | 2(Loss) | true |
| Glaze | 1849.64 | 0.15564 | 1381.78ms | 25388 | 640 | 265648 | 13090.1 | 0.0870572 | 3(Loss) | true |
| simdjson (ondemand) | 1737.34 | 0.064739 | 1415.47ms | 25388 | 4890 | 398041 | 13936.2 | 0.104689 | 4(Loss) | true |

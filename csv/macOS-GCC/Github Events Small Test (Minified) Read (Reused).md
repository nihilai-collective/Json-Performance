
----
### Github Events Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2098.73 | 1.5549 | 100.302ms | 1691 | 1280 | 182722 | 768.4 | 0.259605 | 1(Win) | true |
| Glaze | 1760.74 | 0.811091 | 115.686ms | 1691 | 2560 | 141278 | 915.9 | 0.427632 | 2(Loss) | true |
| Jsonifier (two-stage) | 1702.37 | 0.430751 | 118.23ms | 1691 | 4890 | 81422 | 947.305 | 0.350075 | 3(Loss) | true |
| simdjson (reflection) | 1369.22 | 0.952661 | 143.481ms | 1691 | 1280 | 161150 | 1177.8 | 0.0169779 | 4(Loss) | true |
| simdjson (ondemand) | 1310.49 | 0.508531 | 146.7ms | 1691 | 4890 | 191498 | 1230.58 | 0.751677 | 5(Loss) | true |

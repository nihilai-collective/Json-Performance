
----
### Canada Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1432.4 | 0.304479 | 912.566ms | 11579 | 2560 | 1.41048e+06 | 7709.15 | 0.175241 | 1(Win) | true |
| Jsonifier | 1373.99 | 0.266083 | 893.296ms | 11579 | 2560 | 1.17071e+06 | 8036.9 | 1.47932 | 2(Loss) | true |
| simdjson (ondemand) | 1097.77 | 0.474334 | 1117.08ms | 11579 | 320 | 728514 | 10059.1 | 0.155511 | 3(Loss) | true |
| Glaze | 1010.3 | 0.621884 | 1166.35ms | 11579 | 640 | 2.95694e+06 | 10930 | 1.20554 | 4(Loss) | true |

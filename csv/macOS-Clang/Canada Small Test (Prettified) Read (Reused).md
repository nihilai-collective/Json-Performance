
----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1503.67 | 0.564866 | 924.732ms | 11579 | 320 | 550653 | 7343.76 | 1.55965 | 1(Win) | true |
| Jsonifier (two-stage) | 1251.14 | 1.479 | 933.771ms | 11579 | 80 | 1.36319e+06 | 8826.01 | 0.599012 | 2(Loss) | true |
| Glaze | 1058.45 | 0.331576 | 1195.65ms | 11579 | 640 | 765852 | 10432.8 | 0.549135 | 3(Loss) | true |
| simdjson (ondemand) | 1031.96 | 0.393898 | 1239.48ms | 11579 | 1280 | 2.27403e+06 | 10700.6 | 1.322 | 4(Loss) | true |

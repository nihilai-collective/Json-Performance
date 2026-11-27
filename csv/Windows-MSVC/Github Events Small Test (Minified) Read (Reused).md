
----
### Github Events Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1543.68 | 0.266454 | 129.742ms | 1691 | 320 | 2479.53 | 1044.69 | 0.0299043 | 1.55964 | 1(Win) | true |
| Glaze | 1353.9 | 0.413756 | 143.85ms | 1691 | 4890 | 118772 | 1191.12 | 0.632961 | 1.7871 | 2(Loss) | true |
| Jsonifier (two-stage) | 1274.99 | 0.14933 | 152.788ms | 1691 | 640 | 2283.23 | 1264.84 | 0.0370737 | 1.90215 | 3(Loss) | true |
| simdjson (ondemand) | 715.15 | 0.174961 | 260.647ms | 1691 | 160 | 2490.57 | 2255 | 0.221239 | 3.41775 | 4(Loss) | true |

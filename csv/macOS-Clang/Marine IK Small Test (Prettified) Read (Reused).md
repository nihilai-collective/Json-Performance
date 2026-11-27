
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2386.42 | 0.0324016 | 875.725ms | 18245 | 160 | 892.988 | 7291.16 | 0.0427927 | 1(Win) | true |
| Jsonifier | 2370.68 | 0.0506826 | 897.724ms | 18245 | 80 | 1107.01 | 7339.57 | 0.127569 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 1374.77 | 0.191094 | 1415.02ms | 18245 | 320 | 187185 | 12656.5 | 0.260052 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1369.73 | 0.0522947 | 1422.61ms | 18245 | 80 | 3530.39 | 12703.1 | 0.0239173 | 3(Tie) | true |

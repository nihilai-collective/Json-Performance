
----
### Random Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1196.05 | 0.0354619 | 414.846ms | 5094 | 320 | 663.888 | 4061.72 | 0.0514979 | 1(Win) | true |
| Jsonifier | 1140.02 | 0.614485 | 375.4ms | 5094 | 40 | 27426.6 | 4261.32 | 1.02601 | 2(Loss) | true |
| Glaze | 916.142 | 0.0666491 | 537.345ms | 5094 | 320 | 3996.97 | 5302.69 | 0.00300546 | 3(Loss) | true |
| simdjson (ondemand) | 657.071 | 0.0678899 | 777.245ms | 5094 | 4890 | 123201 | 7393.44 | 0.229861 | 4(Loss) | true |

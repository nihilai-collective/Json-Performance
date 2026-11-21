
----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 694.353 | 0.0527076 | 646.02ms | 4604 | 80 | 888.682 | 6323.46 | 0.0100825 | 1(Win) | true |
| Jsonifier (two-stage) | 573.79 | 0.0745111 | 774.037ms | 4604 | 40 | 1300.37 | 7652.12 | 0.0090397 | 2(Loss) | true |
| Glaze | 395.243 | 0.0682231 | 1130.41ms | 4604 | 80 | 4595.1 | 11108.9 | 0.0141798 | 3(Loss) | true |
| simdjson (ondemand) | 330.833 | 0.158636 | 1332.37ms | 4604 | 1280 | 567367 | 13271.7 | 0.16502 | 4(Loss) | true |

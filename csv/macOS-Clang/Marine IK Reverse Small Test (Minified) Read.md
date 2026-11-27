
----
### Marine IK Reverse Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 643.854 | 0.102943 | 695.665ms | 4604 | 30 | 1478.46 | 6819.43 | 0.142933 | 1(Win) | true |
| Jsonifier (two-stage) | 556.376 | 0.0861995 | 804.566ms | 4604 | 30 | 1388.24 | 7891.63 | 0.105907 | 2(Loss) | true |
| Glaze | 388.99 | 0.0524191 | 1148.64ms | 4604 | 80 | 2800.68 | 11287.5 | 0.0368635 | 3(Loss) | true |
| simdjson (ondemand) | 317.506 | 0.0615604 | 1391ms | 4604 | 4890 | 354388 | 13828.8 | 0.00878718 | 4(Loss) | true |

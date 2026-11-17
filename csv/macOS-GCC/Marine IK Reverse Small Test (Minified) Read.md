
----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 602.64 | 0.22151 | 759.392ms | 4604 | 2560 | 666780 | 7285.8 | 0.286304 | 1(Win) | true |
| Jsonifier (two-stage) | 436.349 | 0.883345 | 934.096ms | 4604 | 640 | 5.05642e+06 | 10062.4 | 2.58543 | 2(Loss) | true |
| simdjson (reflection) | 420.662 | 0.408534 | 1035.57ms | 4604 | 4890 | 8.89138e+06 | 10437.6 | 2.0888 | 3(Loss) | true |
| Glaze STATISTICAL TIE | 351.64 | 1.5818 | 1202.21ms | 4604 | 80 | 3.1208e+06 | 12486.4 | 2.64471 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 345.34 | 0.205814 | 1302.63ms | 4604 | 4890 | 3.3484e+06 | 12714.2 | 0.197847 | 4(Tie) | true |

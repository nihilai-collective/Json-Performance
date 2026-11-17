
----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 564.136 | 0.15657 | 952.759ms | 4604 | 4890 | 726159 | 7783.09 | 0.135217 | 4.37304 | 1(Win) | true |
| Jsonifier (two-stage) | 545.431 | 0.176183 | 1012.47ms | 4604 | 30 | 6034.48 | 8050 | 0.0827472 | 4.5195 | 2(Loss) | true |
| Glaze | 165.292 | 0.168462 | 2770.56ms | 4604 | 4890 | 9.79219e+06 | 26563.4 | 0.145627 | 14.9624 | 3(Loss) | true |
| simdjson (ondemand) | 103.539 | 0.278694 | 4422.68ms | 4604 | 320 | 4.46964e+06 | 42406.6 | 0.103797 | 23.8972 | 4(Loss) | true |

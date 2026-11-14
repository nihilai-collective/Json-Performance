
----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 638.919 | 0.163054 | 693.115ms | 4604 | 2560 | 321426 | 6872.1 | 0.205599 | 1(Win) | true |
| Jsonifier (two-stage) | 528.815 | 1.03146 | 927.802ms | 4604 | 30 | 220035 | 8302.93 | 0.412797 | 2(Loss) | true |
| simdjson (reflection) | 458.13 | 1.51299 | 979.65ms | 4604 | 80 | 1.68211e+06 | 9584 | 1.11411 | 3(Loss) | true |
| Glaze | 426.431 | 0.235115 | 1109.02ms | 4604 | 4890 | 2.86579e+06 | 10296.4 | 0.739027 | 4(Loss) | true |
| simdjson (ondemand) | 339.595 | 0.193866 | 1298.76ms | 4604 | 4890 | 3.07227e+06 | 12929.3 | 0.899457 | 5(Loss) | true |

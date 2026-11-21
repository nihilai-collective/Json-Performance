
----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 576.333 | 0.243471 | 918.017ms | 4604 | 4890 | 1.68239e+06 | 7618.36 | 0.012881 | 4.28033 | 1(Win) | true |
| Jsonifier (two-stage) | 537.093 | 0.165204 | 965.274ms | 4604 | 4890 | 891916 | 8174.97 | 0.0686578 | 4.59288 | 2(Loss) | true |
| Glaze | 185.126 | 0.076812 | 2687.58ms | 4604 | 40 | 13275.6 | 23717.5 | 0.220867 | 13.3548 | 3(Loss) | true |
| simdjson (ondemand) | 109.166 | 0.102643 | 4278.61ms | 4604 | 2560 | 4.36315e+06 | 40220.7 | 1.05741 | 22.6651 | 4(Loss) | true |

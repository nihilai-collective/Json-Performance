
----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 442.972 | 0.271304 | 995.309ms | 4604 | 2560 | 1.85127e+06 | 9911.95 | 0.155033 | 5.56185 | 1(Win) | true |
| Jsonifier (two-stage) | 432.867 | 0.248705 | 1080.53ms | 4604 | 30 | 19092 | 10143.3 | 0.131277 | 5.69301 | 2(Loss) | true |
| Glaze | 158.323 | 0.109349 | 2791.58ms | 4604 | 2560 | 2.35426e+06 | 27732.7 | 0.31508 | 15.6098 | 3(Loss) | true |
| simdjson (ondemand) | 99.1468 | 0.1012 | 4421.89ms | 4604 | 2560 | 5.14178e+06 | 44285 | 0.477904 | 24.9556 | 4(Loss) | true |

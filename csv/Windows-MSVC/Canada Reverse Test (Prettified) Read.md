
----
### Canada Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 921.777 | 0.515735 | 8107.51ms | 5212421 | 80 | 6.18829e+10 | 5.3928e+06 | 0.356885 | 3.2972 | 1(Win) | true |
| simdjson (ondemand) | 878.184 | 0.582289 | 8534.94ms | 5212421 | 40 | 4.34555e+10 | 5.66049e+06 | 0.157497 | 3.46086 | 2(Loss) | true |

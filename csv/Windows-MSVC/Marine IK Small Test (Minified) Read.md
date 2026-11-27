
----
### Marine IK Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 170.739 | 0.340286 | 2699.04ms | 4604 | 320 | 2.45043e+06 | 25715.9 | 0.255751 | 14.4851 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 169.053 | 0.999652 | 2631.39ms | 4604 | 40 | 2.6964e+06 | 25972.5 | 0.176781 | 14.628 | 1(Tie) | true |

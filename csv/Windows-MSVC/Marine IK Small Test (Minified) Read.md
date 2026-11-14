
----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 294.245 | 0.0971876 | 1514.9ms | 4604 | 1280 | 269205 | 14922 | 0.122138 | 10.3122 | 1(Win) | true |
| Jsonifier (generic) | 288.652 | 0.133369 | 1577.02ms | 4604 | 640 | 263398 | 15211.1 | 0.0338865 | 10.5137 | 2(Loss) | true |

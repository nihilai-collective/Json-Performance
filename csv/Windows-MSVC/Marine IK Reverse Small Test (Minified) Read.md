
----
### Marine IK Reverse Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 447.198 | 0.222797 | 1005.69ms | 4604 | 2560 | 1.22498e+06 | 9818.28 | 0.0772434 | 5.52074 | 1(Win) | true |
| Jsonifier (two-stage) | 428.559 | 0.420512 | 1102.75ms | 4604 | 320 | 593959 | 10245.3 | 0.494719 | 5.75953 | 2(Loss) | true |
| Glaze | 155.744 | 0.332482 | 2844.22ms | 4604 | 320 | 2.81147e+06 | 28191.9 | 0.179251 | 15.8796 | 3(Loss) | true |
| simdjson (ondemand) | 100.547 | 0.371097 | 4542.34ms | 4604 | 160 | 4.20168e+06 | 43668.1 | 0.0472089 | 24.6033 | 4(Loss) | true |

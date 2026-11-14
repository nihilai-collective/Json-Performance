
----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1791.54 | 0.075176 | 753.054ms | 11579 | 2560 | 54965.2 | 6163.75 | 0.0393077 | 1.69112 | 1(Win) | true |
| Jsonifier | 1725.21 | 0.0550428 | 772.438ms | 11579 | 4890 | 60697 | 6400.72 | 0.00507971 | 1.7559 | 2(Loss) | true |
| simdjson (ondemand) | 968.994 | 0.150744 | 1278.73ms | 11579 | 320 | 94434.9 | 11395.9 | 0.162052 | 3.12956 | 3(Loss) | true |
| Glaze | 856.887 | 0.231643 | 1414.89ms | 11579 | 320 | 285156 | 12886.9 | 0.0823803 | 3.54162 | 4(Loss) | true |

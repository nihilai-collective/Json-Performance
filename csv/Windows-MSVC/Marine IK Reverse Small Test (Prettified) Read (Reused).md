
----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1740.14 | 0.0871012 | 1127.64ms | 18245 | 1280 | 97090.6 | 9999.06 | 0.0375176 | 1.74194 | 1(Win) | true |
| Jsonifier | 1443.44 | 0.0557205 | 1339.51ms | 18245 | 4890 | 220612 | 12054.4 | 0.034651 | 2.1008 | 2(Loss) | true |
| Glaze | 976.094 | 0.0853365 | 1904.55ms | 18245 | 1280 | 296199 | 17825.9 | 0.0490617 | 3.10937 | 3(Loss) | true |
| simdjson (ondemand) | 585.506 | 0.154618 | 3115.76ms | 18245 | 160 | 337805 | 29717.5 | 0.0840548 | 5.18587 | 4(Loss) | true |

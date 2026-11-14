
----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1988.16 | 0.0696102 | 1000.2ms | 18245 | 2560 | 95010.7 | 8751.72 | 0.101869 | 1.52517 | 1(Win) | true |
| Jsonifier | 1651.03 | 0.0685531 | 1198.08ms | 18245 | 80 | 4175.63 | 10538.8 | 0.082958 | 1.83681 | 2(Loss) | true |
| Glaze | 1101.47 | 0.0486071 | 1701.67ms | 18245 | 2560 | 150932 | 15796.9 | 0.0529459 | 2.75514 | 3(Loss) | true |
| simdjson (ondemand) | 667.236 | 0.0481635 | 2745.43ms | 18245 | 4890 | 771390 | 26077.4 | 0.206849 | 4.55094 | 4(Loss) | true |

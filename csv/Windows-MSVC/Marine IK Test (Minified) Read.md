
----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21712 | 0.351562 | 7963.72ms | 1834197 | 160 | 1.28356e+07 | 80565 | 0.00775831 | 0.113993 | 1(Win) | true |
| simdjson (stage-1) | 17965.5 | 0.205274 | 5061.89ms | 1834197 | 320 | 1.2783e+07 | 97365.9 | 0.425373 | 0.137758 | 2(Loss) | true |

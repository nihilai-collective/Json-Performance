
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2268.75 | 0.0277443 | 1600.25ms | 18245 | 4890 | 22139.7 | 7669.33 | 0.069334 | 2.27127 | 9.09591 | 1.72237 | 0.00255569 | 1.44253e-05 | 4.56186e-06 | 1(Win) | true |
| simdjson (ondemand) | 2246.43 | 0.105071 | 1601.67ms | 18245 | 320 | 21194.2 | 7745.52 | 0.103554 | 2.30343 | 9.61829 | 1.65696 | 0.00294224 | 2.0211e-05 | 5.48095e-06 | 2(Loss) | true |

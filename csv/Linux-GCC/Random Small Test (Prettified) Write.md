
----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 27101.3 | 0.0682585 | 35.1866ms | 9255 | 640 | 31.6276 | 325.677 | 0.164833 | 0.0840748 | 1(Win) | true |
| Glaze | 4447.97 | 0.144437 | 210.421ms | 9255 | 30 | 246.437 | 1984.33 | 0.117726 | 0.549289 | 2(Loss) | true |
| simdjson (reflection) | 574.825 | 0.0855468 | 1546.41ms | 9255 | 4890 | 843720 | 15354.7 | 0.687712 | 4.2998 | 3(Loss) | true |

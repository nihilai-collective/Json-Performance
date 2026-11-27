
----
### Marine IK Reverse Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2854.06 | 0.106648 | 5113.4ms | 10018896 | 80 | 1.01978e+09 | 3.34778e+06 | 0.451277 | 0.867447 | 1(Win) | true |
| Glaze | 1463.15 | 0.575313 | 9780.69ms | 9930228 | 30 | 4.1598e+10 | 6.47249e+06 | 1.27279 | 1.69209 | 2(Loss) | true |


----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 659.19 | 0.255957 | 8419.48ms | 1922245 | 30 | 1.52003e+09 | 2.78098e+06 | 1.46821 | 3.75551 | 1(Win) | true |
| Glaze | 420.832 | 0.364873 | 6531.41ms | 1833577 | 80 | 1.83888e+10 | 4.15518e+06 | 0.915773 | 5.88276 | 2(Loss) | true |

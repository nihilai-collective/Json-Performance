
----
### Marine IK Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 952.988 | 1.60149 | 5736.51ms | 1922245 | 40 | 3.79623e+10 | 1.92363e+06 | 0.345886 | 3.18887 | 1(Win) | true |
| Glaze | 574.971 | 0.328154 | 9565.67ms | 1833577 | 160 | 1.59361e+10 | 3.04126e+06 | 0.445865 | 5.28578 | 2(Loss) | true |

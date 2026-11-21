
----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2289.05 | 0.328711 | 6537.91ms | 10018896 | 30 | 5.64782e+09 | 4.17413e+06 | 1.88783 | 1.08158 | 1(Win) | true |
| Glaze | 1087.88 | 1.68956 | 5851.01ms | 9930228 | 40 | 8.65302e+11 | 8.70521e+06 | 1.98889 | 2.27574 | 2(Loss) | true |

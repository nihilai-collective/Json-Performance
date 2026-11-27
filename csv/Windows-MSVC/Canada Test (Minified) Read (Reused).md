
----
### Canada Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 793.753 | 0.541815 | 10082.2ms | 2251027 | 160 | 3.43569e+10 | 2.70455e+06 | 2.01075 | 3.82839 | 1(Win) | true |
| Jsonifier (two-stage) | 733.676 | 0.849765 | 5446.1ms | 2251027 | 40 | 2.47293e+10 | 2.92602e+06 | 0.533415 | 4.1417 | 2(Loss) | true |
| simdjson (ondemand) | 452.454 | 0.78802 | 8044.95ms | 2251027 | 80 | 1.11835e+11 | 4.74467e+06 | 1.5302 | 6.71724 | 3(Loss) | true |
| Glaze | 388.257 | 1.74965 | 9132.25ms | 2251027 | 80 | 7.4871e+11 | 5.52919e+06 | 1.73581 | 7.82799 | 4(Loss) | true |

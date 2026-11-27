
----
### Instruments Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13952.9 | 0.0846274 | 750.765ms | 4669 | 160 | 11.6698 | 319.125 | 0.175953 | 0.415488 | 1.34911 | 0.178197 | 0.000215517 | 2.81109e-05 | 4.01585e-06 | 1(Win) | true |
| simdjson (reflection) | 10676.8 | 0.188722 | 761.229ms | 4669 | 640 | 396.453 | 417.045 | 0.881026 | 0.530592 | 1.6239 | 0.188477 | 0.000214179 | 1.87406e-05 | 1.67327e-06 | 2(Loss) | true |
| Glaze | 3952.34 | 0.395334 | 833.06ms | 4669 | 80 | 1586.93 | 1126.6 | 0.0732828 | 1.35099 | 3.43993 | 0.494969 | 0.000428357 | 2.94496e-05 | 2.67723e-06 | 3(Loss) | true |

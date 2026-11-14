
----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10225.1 | 0.420924 | 770.12ms | 4857 | 1280 | 4653.88 | 453.001 | 0.189202 | 0.547577 | 1.67037 | 0.276302 | 0.000207014 | 3.49045e-05 | 1.25463e-05 | 1(Win) | true |
| simdjson (reflection) | 7829.61 | 0.175065 | 783.553ms | 4857 | 30 | 32.1793 | 591.6 | 0.0563761 | 0.705785 | 2.06485 | 0.334569 | 0.000205888 | 3.43147e-05 | 1.37259e-05 | 2(Loss) | true |
| Glaze | 3769.99 | 0.133113 | 851.994ms | 4857 | 4890 | 13080 | 1228.65 | 0.309492 | 1.39977 | 3.69673 | 0.602636 | 0.000209846 | 7.84818e-05 | 3.28411e-05 | 3(Loss) | true |

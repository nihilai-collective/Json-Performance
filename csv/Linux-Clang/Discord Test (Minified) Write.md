
----
### Discord Test (Minified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12658.4 | 0.102413 | 1166.34ms | 56369 | 1280 | 24212.5 | 4246.78 | 0.223236 | 0.403933 | 1.50946 | 0.214551 | 0.000170431 | 8.45434e-06 | 3.49261e-06 | 1(Win) | true |
| Glaze | 5048.67 | 0.0939156 | 1806.15ms | 56369 | 2560 | 256001 | 10647.9 | 0.284073 | 1.00158 | 3.48977 | 0.484735 | 0.000113046 | 1.90916e-05 | 8.87012e-06 | 2(Loss) | true |

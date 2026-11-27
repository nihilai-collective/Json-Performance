
----
### Instruments Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3069.98 | 1.62332 | 5967.59ms | 183677 | 640 | 5.49072e+08 | 57058.4 | 0.504761 | 0.989487 | 1(Win) | true |
| Jsonifier (two-stage) | 2636.57 | 0.614217 | 6890.62ms | 183677 | 2560 | 4.26301e+08 | 66438 | 0.0538276 | 1.15219 | 2(Loss) | true |
| Glaze | 2136.85 | 0.354142 | 8813.18ms | 183677 | 40 | 3.37115e+06 | 81975 | 0.00203318 | 1.42192 | 3(Loss) | true |
| simdjson (ondemand) | 1658.22 | 0.255818 | 5674.8ms | 183677 | 160 | 1.16845e+07 | 105636 | 2.03672 | 1.83246 | 4(Loss) | true |

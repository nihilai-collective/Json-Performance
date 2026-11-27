
----
### Github Events Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10402.2 | 0.15946 | 735.739ms | 1996 | 320 | 27.2476 | 182.994 | 0.0682617 | 0.601577 | 1.35721 | 0.203908 | 0.000501002 | 2.50501e-05 | 3.13126e-06 | 1(Win) | true |
| simdjson (reflection) | 7614.14 | 0.12609 | 742.76ms | 1996 | 80 | 7.94937 | 250 | 0.020004 | 0.794282 | 1.70541 | 0.231463 | 0.000501002 | 0 | 0 | 2(Loss) | true |
| Glaze | 5376.26 | 0.470877 | 752.016ms | 1996 | 4890 | 13592 | 354.063 | 0.529485 | 1.06595 | 2.96042 | 0.462926 | 0.000501412 | 2.9302e-05 | 1.07577e-05 | 3(Loss) | true |

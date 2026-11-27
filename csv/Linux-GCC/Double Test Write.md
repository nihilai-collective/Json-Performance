
----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 381.875 | 0.0328211 | 1215.95ms | 1997 | 4890 | 13101.8 | 4987.21 | 0.224039 | 13.6287 | 56.4497 | 9.65849 | 0.0128504 | 0.000191699 | 5.12015e-05 | 1(Win) | true |
| simdjson (reflection) | 366.342 | 0.0362943 | 1239.26ms | 1997 | 4890 | 17408.8 | 5198.66 | 0.0310602 | 14.1213 | 60.2429 | 10.7807 | 0.00858691 | 0.000198662 | 7.51639e-05 | 2(Loss) | true |
| Glaze | 272.417 | 0.0955313 | 1354.16ms | 1798 | 1280 | 46282 | 6294.42 | 0.705219 | 19.0797 | 77.9839 | 14.5161 | 0.0113985 | 0.000240284 | 7.56048e-05 | 3(Loss) | true |


----
### Twitter Partial Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6798.86 | 0.0800949 | 769.146ms | 3808 | 1280 | 234.283 | 534.147 | 0.0178407 | 0.8163 | 3.2416 | 0.40021 | 0.000263015 | 1.78489e-05 | 4.92384e-06 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 6742.21 | 0.0913501 | 770.556ms | 3808 | 2560 | 619.794 | 538.635 | 0.141217 | 0.827369 | 3.30882 | 0.332458 | 0.000302406 | 9.95027e-06 | 2.97482e-06 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 6719.79 | 0.23351 | 770.061ms | 3808 | 1280 | 2038.46 | 540.432 | 0.0160488 | 0.82322 | 3.2416 | 0.40021 | 0.000263426 | 2.1747e-05 | 5.94965e-06 | 2(Tie) | true |
| simdjson (reflection) | 6625.44 | 0.0678806 | 769.894ms | 3808 | 320 | 44.3001 | 548.128 | 0.0894291 | 0.834975 | 3.29254 | 0.33666 | 0.000273273 | 1.55922e-05 | 5.74449e-06 | 4(Loss) | true |
| Glaze | 3563.78 | 0.0571021 | 815.349ms | 3808 | 4890 | 1655.71 | 1019.03 | 0.148386 | 1.50845 | 6.58508 | 1.20746 | 0.000264538 | 9.77385e-06 | 3.54436e-06 | 5(Loss) | true |

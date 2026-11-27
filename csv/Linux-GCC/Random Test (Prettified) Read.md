
----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1853.12 | 0.0794265 | 9718.47ms | 728486 | 640 | 5.67476e+07 | 374903 | 0.0191351 | 1.33588 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1634.58 | 0.259067 | 5498.09ms | 728486 | 80 | 9.69942e+07 | 425027 | 0.129113 | 1.5145 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1630.66 | 0.127772 | 5431.21ms | 728486 | 160 | 4.74141e+07 | 426048 | 2.00091 | 1.51814 | 2(Tie) | true |
| simdjson (reflection) | 1622.95 | 0.210085 | 5424.63ms | 728486 | 40 | 3.23509e+07 | 428072 | 0.624876 | 1.52536 | 4(Loss) | true |
| Glaze | 1279.52 | 0.254559 | 6894.55ms | 728486 | 30 | 5.73121e+07 | 542969 | 0.219132 | 1.93481 | 5(Loss) | true |

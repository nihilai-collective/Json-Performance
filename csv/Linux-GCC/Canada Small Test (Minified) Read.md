
----
### Canada Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 928.392 | 0.0791312 | 1206.1ms | 4630 | 80 | 1133.14 | 4756.09 | 0.0317912 | 5.59668 | 26.4309 | 5.69719 | 0.00345842 | 0.00011879 | 8.63931e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 783.009 | 0.14622 | 1294.86ms | 4630 | 320 | 21756.5 | 5639.16 | 0.0834708 | 6.60951 | 29.6672 | 6.11059 | 0.0031466 | 4.45464e-05 | 1.2824e-05 | 2(Loss) | true |
| simdjson (reflection) | 757.119 | 0.0965984 | 1318.93ms | 4630 | 320 | 10156 | 5831.99 | 0.0750199 | 6.83845 | 27.9585 | 5.18035 | 0.00978334 | 2.83477e-05 | 6.07451e-06 | 3(Loss) | true |
| Glaze | 723.66 | 0.0250999 | 1334.25ms | 4630 | 4890 | 11469.5 | 6101.64 | 0.270194 | 7.05832 | 30.5838 | 5.84255 | 0.0057519 | 0.000103884 | 3.70572e-05 | 4(Loss) | true |
| simdjson (ondemand) | 665.85 | 0.103375 | 1388.4ms | 4630 | 80 | 3759.51 | 6631.39 | 0.264026 | 7.78438 | 31.1352 | 6.01058 | 0.00784017 | 0.000275378 | 0.000197084 | 5(Loss) | true |


----
### Twitter Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3641.18 | 0.0419991 | 804.163ms | 2889 | 1280 | 129.271 | 756.669 | 0.213768 | 1.49099 | 4.75839 | 0.766701 | 0.000346141 | 4.73239e-05 | 5.67887e-06 | 1(Win) | true |
| Glaze | 2621.25 | 0.047989 | 831.267ms | 2889 | 2560 | 651.332 | 1051.09 | 0.0562233 | 2.04032 | 8.32399 | 1.40222 | 0.000347087 | 5.09746e-05 | 1.09521e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2494.41 | 0.0618326 | 836.16ms | 2889 | 4890 | 2280.89 | 1104.54 | 0.00881217 | 2.13343 | 7.69263 | 1.07684 | 0.000349963 | 5.42924e-05 | 1.21751e-05 | 3(Loss) | true |
| simdjson (reflection) | 2109.23 | 0.069252 | 858.082ms | 2889 | 4890 | 4001.48 | 1306.24 | 0.158425 | 2.51603 | 8.67047 | 1.15888 | 0.000351237 | 5.40092e-05 | 1.28122e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1421.99 | 0.103932 | 925.889ms | 2889 | 1280 | 5190.52 | 1937.54 | 0.221412 | 3.68499 | 11.6314 | 2.28557 | 0.00128856 | 4.75943e-05 | 7.3014e-06 | 5(Loss) | true |

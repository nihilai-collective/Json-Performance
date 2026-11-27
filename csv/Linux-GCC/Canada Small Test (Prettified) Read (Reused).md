
----
### Canada Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2333.58 | 0.0525712 | 1294.08ms | 11579 | 2560 | 15842.9 | 4732.04 | 0.0623845 | 2.21291 | 10.7749 | 2.26116 | 0.00168391 | 4.98613e-05 | 2.94175e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2238.86 | 0.100073 | 1320.82ms | 11579 | 640 | 15591.9 | 4932.24 | 0.286439 | 2.28627 | 10.8496 | 2.07445 | 0.00127008 | 1.80823e-05 | 4.58805e-06 | 2(Loss) | true |
| simdjson (reflection) | 1995.28 | 0.0342649 | 1380.24ms | 11579 | 4890 | 17585 | 5534.37 | 0.169564 | 2.55559 | 10.7243 | 1.81769 | 0.0028413 | 3.91549e-05 | 2.34364e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1745.47 | 0.0579399 | 1460.67ms | 11579 | 640 | 8599.08 | 6326.42 | 0.0104978 | 2.91377 | 11.9738 | 2.14682 | 0.00179595 | 1.25497e-05 | 2.69885e-07 | 4(Loss) | true |
| Glaze | 1562.75 | 0.0463241 | 1529.05ms | 11579 | 1280 | 13714.7 | 7066.11 | 0.227616 | 3.27927 | 13.7408 | 2.48778 | 0.00516972 | 5.35047e-05 | 2.73933e-05 | 5(Loss) | true |

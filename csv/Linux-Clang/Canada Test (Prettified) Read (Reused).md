
----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2196.98 | 0.0705805 | 8426.96ms | 5373214 | 80 | 2.16808e+08 | 2.33243e+06 | 0.0126783 | 2.29796 | 12.5941 | 2.51409 | 0.00307514 | 0.0281069 | 0.000345091 | 1(Win) | true |
| Jsonifier (two-stage) | 2183.67 | 0.217983 | 8437.71ms | 5373214 | 40 | 1.04664e+09 | 2.34664e+06 | 0.0306112 | 2.29824 | 12.2637 | 2.22175 | 0.00431268 | 0.0523078 | 0.00202849 | 2(Loss) | true |
| simdjson (ondemand) | 2130.91 | 0.0972797 | 8663.94ms | 5373214 | 80 | 4.37798e+08 | 2.40475e+06 | 0.475058 | 2.37347 | 11.7272 | 1.8044 | 0.00486193 | 0.050817 | 0.00044911 | 3(Loss) | true |
| Glaze | 1951.88 | 0.0950943 | 9357.11ms | 5373214 | 40 | 2.49305e+08 | 2.62531e+06 | 0.00848828 | 2.58608 | 13.9455 | 2.50089 | 0.00465173 | 0.0297269 | 0.000385654 | 4(Loss) | true |

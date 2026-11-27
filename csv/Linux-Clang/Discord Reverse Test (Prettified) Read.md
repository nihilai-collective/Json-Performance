
----
### Discord Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 918.335 | 0.129839 | 9532.79ms | 83958 | 80 | 1.02524e+06 | 87188.9 | 0.0173157 | 5.57841 | 25.1771 | 5.16025 | 0.00777919 | 7.72708e-05 | 6.05958e-05 | 1(Win) | true |
| simdjson (ondemand) | 293.269 | 0.104976 | 7148ms | 83958 | 320 | 2.62858e+07 | 273021 | 0.0357559 | 17.2629 | 93.9415 | 18.8189 | 0.0259009 | 0.000439505 | 0.000353153 | 2(Loss) | true |

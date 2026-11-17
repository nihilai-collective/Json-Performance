
----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3401.28 | 0.163852 | 269.258ms | 9378 | 30 | 556.878 | 2629.47 | 0.608364 | 0.720278 | 1(Win) | true |
| Jsonifier | 2897.47 | 0.293054 | 311.267ms | 9378 | 2560 | 209469 | 3086.68 | 0.254051 | 0.846978 | 2(Loss) | true |
| Glaze | 2412.27 | 0.0559465 | 375.657ms | 9378 | 160 | 688.389 | 3707.53 | 0.274361 | 1.01866 | 3(Loss) | true |
| simdjson (ondemand) | 1927.98 | 0.459238 | 465.842ms | 9378 | 640 | 290448 | 4638.81 | 0.125864 | 1.27631 | 4(Loss) | true |

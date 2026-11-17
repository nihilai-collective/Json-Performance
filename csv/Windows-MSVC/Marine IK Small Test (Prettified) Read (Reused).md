
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1878.58 | 0.0784201 | 1055.87ms | 18245 | 1280 | 67529.2 | 9262.19 | 0.048946 | 1.61368 | 1(Win) | true |
| Jsonifier | 1672.16 | 0.0755777 | 1167.15ms | 18245 | 2560 | 158328 | 10405.5 | 0.0292898 | 1.81317 | 2(Loss) | true |
| simdjson (ondemand) | 1109.18 | 0.104872 | 1680.65ms | 18245 | 640 | 173212 | 15687 | 0.0865809 | 2.73604 | 3(Loss) | true |
| Glaze | 983.803 | 0.327741 | 1923.22ms | 18245 | 80 | 268796 | 17686.2 | 0.00706714 | 3.08574 | 4(Loss) | true |


----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2309 | 0.11348 | 1074ms | 8051 | 2560 | 36452.9 | 3325.26 | 0.167785 | 2.2205 | 9.74413 | 1.67706 | 0.000980759 | 4.81792e-05 | 1.89223e-05 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 1672.11 | 0.229709 | 1198.06ms | 8051 | 1280 | 142409 | 4591.84 | 0.0959653 | 3.04994 | 11.5796 | 2.34617 | 0.00397612 | 5.06536e-05 | 2.29979e-05 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1664.56 | 0.0972464 | 1201.29ms | 8051 | 2560 | 51509.4 | 4612.64 | 0.0769284 | 3.05876 | 13.2225 | 2.5772 | 0.00331413 | 3.85725e-05 | 1.1693e-05 | 2(Tie) | true |
| simdjson (ondemand) | 1291.2 | 0.0885483 | 1338.55ms | 8051 | 2560 | 70976.7 | 5946.45 | 0.0566507 | 3.93551 | 14.6793 | 2.44305 | 0.00376254 | 4.80821e-05 | 2.01353e-05 | 4(Loss) | true |

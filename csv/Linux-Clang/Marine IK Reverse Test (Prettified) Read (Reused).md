
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2726.9 | 0.0678911 | 8692.8ms | 7351818 | 160 | 4.87525e+08 | 2.57114e+06 | 0.0337936 | 1.84475 | 8.0654 | 1.51252 | 0.00959089 | 0.0541928 | 0.00224531 | 1(Win) | true |
| Jsonifier | 2639.94 | 0.0688551 | 8928.89ms | 7351818 | 160 | 5.35052e+08 | 2.65584e+06 | 0.40169 | 1.89018 | 8.86404 | 2.10027 | 0.00666903 | 0.0271144 | 0.000529907 | 2(Loss) | true |
| simdjson (ondemand) | 2322.86 | 0.0664067 | 10085.8ms | 7351818 | 160 | 6.42816e+08 | 3.01836e+06 | 0.083569 | 2.1666 | 9.45645 | 1.4366 | 0.0098263 | 0.0536423 | 0.000998854 | 3(Loss) | true |
| Glaze | 2255.31 | 0.103387 | 5014.71ms | 7351818 | 80 | 8.26421e+08 | 3.10876e+06 | 0.174772 | 2.22926 | 10.2813 | 2.06793 | 0.00882154 | 0.0273407 | 0.000408477 | 4(Loss) | true |
